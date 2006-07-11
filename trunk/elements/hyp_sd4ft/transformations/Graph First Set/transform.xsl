<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xl3DColumn</xsl:variable>
<xsl:variable name="GraphTitle">SD-4ft Graph - first set</xsl:variable>
<xsl:variable name="LegendShow">false</xsl:variable>
<xsl:variable name="GraphWidth">1</xsl:variable>
<xsl:variable name="GraphHeight">0,75</xsl:variable>

	
	


	<xsl:template match="hyp_sd4ft"> 
	<xsl:variable name="id_base" select="@id" />

	
		<paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{$id_base}_4ftgraph1">
				<categories id="{$id_base}categories1">
					<category title="succedent" id="{$id_base}category1_1" />
					<category title="not succedent" id="{$id_base}category2_1" />
				</categories>
				<chart title="antecend" id="{$id_base}chart1_1">
					<value value="{@a}" id="{$id_base}value1_1"/>
					<value value="{@b}" id="{$id_base}value2_1"/>
				</chart>			
				<chart title="not antecend" id="{$id_base}chart2_1">
					<value value="{@c}" id="{$id_base}value3_1"/>
					<value value="{@d}" id="{$id_base}value4_1"/>
				</chart>			
			</graph>
		</paragraph>
	

	</xsl:template>
      




</xsl:stylesheet>
