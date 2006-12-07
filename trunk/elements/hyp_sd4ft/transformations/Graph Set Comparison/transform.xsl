<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">


<!-- nastaveni jazyka (defaultne cestina)-->
<xsl:variable name="lng">cz</xsl:variable>
      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xlColumnStacked</xsl:variable>
<xsl:variable name="ValuesType">abs</xsl:variable>
<xsl:variable name="GraphTitle">SD-4ft Graph</xsl:variable>
<xsl:variable name="LegendShow">false</xsl:variable>
<xsl:variable name="GraphWidth">75e-2</xsl:variable>
<xsl:variable name="GraphHeight">75e-2</xsl:variable>
<xsl:variable name="Chart1Color">#aa20aa</xsl:variable>
<xsl:variable name="Chart2Color">#4040fc</xsl:variable>
<xsl:variable name="AntecedentLabel">antecedent</xsl:variable>
<xsl:variable name="SuccedentLabel">succedent</xsl:variable>
<xsl:variable name="NotAntecedentLabel">¬ antecedent</xsl:variable>
<xsl:variable name="NotSuccedentLabel">¬ succedent</xsl:variable>



<!-- nastaveni jazykovych popisku (labelu) -->

<xsl:variable name="label_first_set">   <!-- nadpis tabulky: prvni mnozina-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">První množina</xsl:when>
		<xsl:when test="$lng='en'">First set</xsl:when>
		<xsl:otherwise>First set</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_second_set">   <!-- nadpis tabulky: druha mnozina-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Druhá množina</xsl:when>
		<xsl:when test="$lng='en'">Second set</xsl:when>
		<xsl:otherwise>Second set</xsl:otherwise>
	</xsl:choose>
</xsl:variable>



	
<msxsl:script language="JScript" implements-prefix="dedek">

	function max4(a, b, c, d)
	{
		return Math.max(a,b,c,d);
	}
	
	function max2(x, y)
	{
		return Math.max(x,y);
	}
	
	function normalize_value(co, cim)
	{
		return Math.round(100*(co/cim));
	}


</msxsl:script>


  <!--specialni promenna - SpecialString ... pokud je hodnota AntecedentLabel ... NotSuccedentLabel nastavena na tuto
  hodnotu, nahradi se prislusnou hodnotou skutecneho cedentu-->
  <xsl:variable name="SpecialString">***</xsl:variable>



  <xsl:template match="hyp_sd4ft"> <!-- nezpomen prepsat na match="/hyp_4ft" - odebrat lomitko -->


	<!-- hodnoty cisel, souctu a maxima-->
	
	
	<xsl:variable name="sum_set1" select="@a + @b + @c + @d"/>
	<xsl:variable name="max_set1" select="dedek:max4(number(@a), number(@b), number(@c), number(@d))"/>
	<xsl:variable name="sum_set2" select="@e + @f + @g + @h"/>
	<xsl:variable name="max_set2" select="dedek:max4(number(@e), number(@f), number(@g), number(@h))"/>
	
	<!--spocitani hodnot grafu-->
	
	
	
	<!-- First set-->
			
	<xsl:variable name="a">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@a), number($max_set1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@a" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="b">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@b), number($max_set1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@b" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="c">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@c), number($max_set1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@c" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="d">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@d), number($max_set1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@d" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<!-- Second set-->
	
	<xsl:variable name="e">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@e), number($sum_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@e), number($max_set2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@e" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="f">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@f), number($sum_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@f), number($max_set2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@f" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="g">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@g), number($sum_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@g), number($max_set2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@g" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="h">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@h), number($sum_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@h), number($max_set2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@h" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>



    <!--hodnoty cedentu-->
    <xsl:variable name="antecedent_str">
      <xsl:for-each select="id(@antecedent)/ti_literal">
        <xsl:if test="position()!=1">
          <xsl:text disable-output-escaping="no"> &amp; </xsl:text>
        </xsl:if>
        <xsl:value-of select="@quant"/>
        <xsl:text disable-output-escaping="yes">(</xsl:text>
        <xsl:value-of select="@value"/>
        <xsl:text disable-output-escaping="yes">)</xsl:text>
      </xsl:for-each>
      <xsl:if test="count(id(@antecedent)/ti_literal)=0">
        <xsl:choose>
          <xsl:when test="$lng='cz'">bez omezení</xsl:when>
          <xsl:otherwise>no restriction</xsl:otherwise>
        </xsl:choose>
      </xsl:if>
    </xsl:variable>

    <xsl:variable name="succedent_str">
      <xsl:for-each select="id(@succedent)/ti_literal">
        <xsl:if test="position()!=1">
          <xsl:text disable-output-escaping="no"> &amp; </xsl:text>
        </xsl:if>
        <xsl:value-of select="@quant"/>
        <xsl:text disable-output-escaping="yes">(</xsl:text>
        <xsl:value-of select="@value"/>
        <xsl:text disable-output-escaping="yes">)</xsl:text>
      </xsl:for-each>
      <xsl:if test="count(id(@succedent)/ti_literal)=0">
        <xsl:choose>
          <xsl:when test="$lng='cz'">bez omezení</xsl:when>
          <xsl:otherwise>no restriction</xsl:otherwise>
        </xsl:choose>
      </xsl:if>
    </xsl:variable>

    <!--skutecne labely - popisky grafu-->
    <xsl:variable name="a_label">
      <xsl:choose>
        <xsl:when test="$AntecedentLabel=$SpecialString">
          <xsl:value-of select="$antecedent_str" />
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$AntecedentLabel"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="na_label">
      <xsl:choose>
        <xsl:when test="$NotAntecedentLabel=$SpecialString">
          <xsl:text>NOT </xsl:text>
          <xsl:value-of select="$antecedent_str" />
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$NotAntecedentLabel"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="s_label">
      <xsl:choose>
        <xsl:when test="$SuccedentLabel=$SpecialString">
          <xsl:value-of select="$succedent_str" />
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$SuccedentLabel"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="ns_label">
      <xsl:choose>
        <xsl:when test="$NotSuccedentLabel=$SpecialString">
          <xsl:text>NOT </xsl:text>
          <xsl:value-of select="$succedent_str" />
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$NotSuccedentLabel"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>




    <paragraph>
		    	
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_4ftgraph_1">
				<categories id="categories1">
					
						<category title="{$a_label} &amp; {$s_label}" id="category1"></category>
						<category title="{$a_label} &amp; {$ns_label}" id="category2"></category>
					
						<category title="{$na_label} &amp; {$s_label}" id="category3"></category>
						<category title="{$na_label} &amp; {$ns_label}" id="category4"></category>
					
				</categories>

				<chart title="{$label_first_set}" id="chart1_1" color="{$Chart1Color}">
						<value value="{$a}" id="value1_1"></value>
						<value value="{$b}" id="value2_1"></value>
						<value value="{$c}" id="value3_1"></value>
						<value value="{$d}" id="value4_1"></value>					
				</chart>
				
				<chart title="{$label_second_set}" id="chart2_1" color="{$Chart2Color}">
						<value value="{$e}" id="value1_2"></value>
						<value value="{$f}" id="value2_2"></value>
						<value value="{$g}" id="value3_2"></value>
						<value value="{$h}" id="value4_2"></value>
				</chart>							
				
			</graph>
		  
			
		</paragraph>
		

		
								
	
</xsl:template>
      




</xsl:stylesheet>
