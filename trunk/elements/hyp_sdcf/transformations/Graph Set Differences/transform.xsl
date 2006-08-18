<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      xmlns:ms="urn:schemas-microsoft-com:xslt"
      version="1.0">

      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xl3DColumn</xsl:variable>
<xsl:variable name="ValuesType">rel_max</xsl:variable>
<xsl:variable name="DifType">dif_rel</xsl:variable>
<xsl:variable name="GraphTitle">CF Graph</xsl:variable>
<xsl:variable name="LegendShow">true</xsl:variable>
<xsl:variable name="GraphWidth">75e-2</xsl:variable>
<xsl:variable name="GraphHeight">75e-2</xsl:variable>
<xsl:variable name="ChartColor">#aa20aa</xsl:variable>

	

<msxsl:script language="JScript" implements-prefix="dedek">

	
	function normalize_value(co, cim)
	{
		return Math.round(100*(co/cim));
	}
	
	function des_tecka(n)
	{
		return (n.replace(",","."));
	}
	
	function hodnota(val1, val2, nf1, nf2, nf)
	{
		var delitel1 = nf1;
		if (delitel1 == 0)
			delitel1 = 1;
		var delitel2 = nf2;
		if (delitel2 == 0)
			delitel2 = 1;
		var delitel = nf;
		if (delitel == 0)
			delitel = 1;
		
		return (Math.round(Math.abs((val1/delitel1) - (val2/delitel2)) / delitel));
	}
	
	function podel(x,y)
	{
		if (y == 0)
			return (0);
		return (x/y);
	}


</msxsl:script>
	


	
	
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />

<!-- klic - hypotezy -->
<xsl:key name="key_hyp_sdcf" match="hyp_sdcf" use="@id" />	

	
	
<!-- TEMPLATES-->	
	
	
	<xsl:template match="hyp_sdcf"> 


		<xsl:variable name="id_base" select="@id" />
		
		<!-- cim se bude normalizovat (normalizacni faktory)-->
		<xsl:variable name="norm_factor">
			<xsl:choose>
				<xsl:when test="$ValuesType='rel_sum'">
					<xsl:choose>
						<xsl:when test="$DifType='dif_abs'"><xsl:value-of select="number(@da_sum) div 100"/></xsl:when>
						<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="dedek:des_tecka(string(@dr_sum))"/></xsl:when>
					</xsl:choose>
				</xsl:when>
				
				<xsl:when test="$ValuesType='rel_max'">
					<xsl:choose>
						<xsl:when test="$DifType='dif_abs'"><xsl:value-of select="number(@da_max) div 100"/></xsl:when>
						<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="dedek:des_tecka(string(@dr_max))"/></xsl:when>
					</xsl:choose>
				</xsl:when>
				<xsl:otherwise>1</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="norm_factor_set1">
			<xsl:choose>
				<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="number(@sum1) div 100"/></xsl:when>
				<xsl:otherwise>1</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="norm_factor_set2">
			<xsl:choose>
				<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="number(@sum2) div 100"/></xsl:when>
				<xsl:otherwise>1</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		
			
		<paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_sdgraph">
			
			<xsl:for-each select="key('key_ti_attribute',@attributes)">
				<xsl:call-template name="categories" />  <!-- vypsani kategorii-->
			</xsl:for-each>
				
				<xsl:element name="chart">
					<xsl:attribute name="id">chart1</xsl:attribute>				
					<xsl:attribute name="title"><xsl:value-of select="key('key_ti_attribute',@attributes)/@quant" /></xsl:attribute>				
					<xsl:if test="$GraphType!='xl3DPie' and $GraphType!='xlPie'">
						<xsl:attribute name="color"><xsl:value-of select="$ChartColor" /></xsl:attribute>				
					</xsl:if>
						<xsl:for-each select="r[position()=1]/c">
							<xsl:variable name="pozice" select="position()"/>
							<xsl:variable name="val1" select="@val"/>
							<xsl:variable name="val2" select="key('key_hyp_sdcf',$id_base)/r[position()=2]/c[position()=$pozice]/@val"/>
							<xsl:variable name="hodnota">
								<xsl:value-of select="dedek:hodnota(number($val1),number($val2),number($norm_factor_set1),number($norm_factor_set2),number($norm_factor))"/>
								<xsl:if test="$ValuesType!='abs'">%</xsl:if>
							</xsl:variable>
							<value value="{$hodnota}" id="{$id_base}_val{position()}" />	
						</xsl:for-each>
				</xsl:element>			
							
			</graph>
		</paragraph>						
	
	</xsl:template>
	
	
	
	<xsl:template name="categories" >  <!-- vypise kategorie atributu-->
		
			<categories id="{@id}_cats1">
				<xsl:variable name="id_base" select="@id" />
			
				<xsl:for-each select="ti_category" >	
					<category title="{@value}" id="{$id_base}_cat{position()}" />
				</xsl:for-each>
			</categories>
			
	</xsl:template>
      




</xsl:stylesheet>
