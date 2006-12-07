<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
    
    <!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>
    
    
    <!-- definovani klice - dulezite kvuli hledani elementu s danym ID v celem dokumentu -->
    <xsl:key name="attribute_id" match="ti_attribute" use="@id" />
    
          
	
	<xsl:template match="hyp_sdkl">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
				<!-- vygenerovani atributu -->
				
				<xsl:apply-templates select="@*"/>

				<!-- vygenerovani hodnot kontingencnch tabulek -->
				
				
				<xsl:variable name="kategorie_radek" >	
					<xsl:value-of select="@row_attributes" />
				</xsl:variable>
				
				<xsl:variable name="kategorie_sloupec">
					<xsl:value-of select="@column_attributes" />
				</xsl:variable>
				
				<xsl:for-each select="tab" >
				<xsl:variable name="cislo_tabulky" select="position()" />
				
					<xsl:for-each select="r" > <!-- cyklus pres radky-->
				   		<xsl:variable name="cislo_radku" select="position()" />
				   
				  		 <xsl:for-each select="c">  <!-- cyklus pres polozky radku-->
				   				<xsl:variable name="cislo_sloupce" select="position()" />
				   				<xsl:variable name="jmeno" >
				   						<xsl:text>Tab</xsl:text>
				   						<xsl:value-of select="$cislo_tabulky" />
				   						<xsl:text>(</xsl:text>
				   						<xsl:value-of select="key('attribute_id' , $kategorie_radek)/ti_category[$cislo_radku]/@value" />
				   								   				
				   						<xsl:text>;</xsl:text>
				   				
				   						<xsl:value-of select="key('attribute_id' , $kategorie_sloupec)/ti_category[$cislo_sloupce]/@value" />
				   						<xsl:text>)</xsl:text>
				   				</xsl:variable>
				   		
				   				<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
						<attribute name="{$jmeno}" value="{@val}" />
				   
				  		 </xsl:for-each>
				   
					</xsl:for-each>
					
				</xsl:for-each>
				
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>



















	
	<!-- vypise vsechny atributy krome cedentu-->
	
	<xsl:template match="@*">
	
				<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->
				
				<xsl:when test="name()='sum'">
					<xsl:text>Sum</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='min'">
					<xsl:text>Min</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='max'">
					<xsl:text>Max</xsl:text>
				</xsl:when>
						
				
				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">	
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Databáze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datová matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Jméno úlohy</xsl:text>
							</xsl:when>
							
							
							
							
							
							<xsl:when test="name()='chi_sq1'">
								<xsl:text>ChiSq : Chi-kvadrát test 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_s1'">
								<xsl:text>FncS : function-type KL-Quantifier (sum) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_r1'">
								<xsl:text>FncR : function-type KL-Quantifier (row) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c1'">
								<xsl:text>Nepodmíněná entropie H(C) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_r1'">
								<xsl:text>Nepodmíněná entropie H(R) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c_r1'">
								<xsl:text>Podmíněná entropie H(C|R) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='mi1'">
								<xsl:text>Mutual information MI(C,R) normalizovaná 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='aic1'">
								<xsl:text>Asymetrický informační koeficient AIC(R,C) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='kend1'">
								<xsl:text>Kendallův coefficient 1</xsl:text>
							</xsl:when>
							
							
							
							
							<xsl:when test="name()='chi_sq2'">
								<xsl:text>ChiSq : Chi-kvadrát test 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_s2'">
								<xsl:text>FncS : function-type KL-Quantifier (sum) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_r2'">
								<xsl:text>FncR : function-type KL-Quantifier (row) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c2'">
								<xsl:text>Nepodmíněná entropie H(C) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_r2'">
								<xsl:text>Nepodmíněná entropie H(R) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c_r2'">
								<xsl:text>Podmíněná entropie H(C|R) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='mi2'">
								<xsl:text>Mutual information MI(C,R) normalizovaná 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='aic2'">
								<xsl:text>Asymetrický informační koeficient AIC(R,C) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='kend2'">
								<xsl:text>Kendallův coefficient 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='da_sum'">
								<xsl:text>DA-Sum : Součet rozdílů absolutních frekvencí</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='da_min'">
								<xsl:text>DA-Min : Minimum z rozdílů absolutních frekvencí</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='da_max'">
								<xsl:text>DA-Max : Maximum z rozdílů absolutních frekvencí</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='dr_sum'">
								<xsl:text>D%-Sum : Součet rozdílů relativních frekvencí</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='dr_min'">
								<xsl:text>D%-Min : Minimum z rozdílů relativních frekvencí</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='dr_max'">
								<xsl:text>D%-Max : Maximum z rozdílů relativních frekvencí</xsl:text>
							</xsl:when>

							
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">    
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Database</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Data matrix</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Task name</xsl:text>
							</xsl:when>
							
						
							
							<xsl:when test="name()='chi_sq1'">
								<xsl:text>ChiSq : Chi-square test 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_s1'">
								<xsl:text>FncS : function-type KL-Quantifier (sum) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_r1'">
								<xsl:text>FncR : function-type KL-Quantifier (row) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c1'">
								<xsl:text>Unconditional entropy H(C) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_r1'">
								<xsl:text>Unconditional entropy H(R) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c_r1'">
								<xsl:text>Conditional entropy H(C|R) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='mi1'">
								<xsl:text>Mutual information MI(C,R) normalized 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='aic1'">
								<xsl:text>Asymetric information coefficient AIC(R,C) 1</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='kend1'">
								<xsl:text>Kendall coefficient 1</xsl:text>
							</xsl:when>
							
							
							
							
							<xsl:when test="name()='chi_sq2'">
								<xsl:text>ChiSq : Chi-square test 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_s2'">
								<xsl:text>FncS : function-type KL-Quantifier (sum) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_r2'">
								<xsl:text>FncR : function-type KL-Quantifier (row) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c2'">
								<xsl:text>Unconditional entropy H(C) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_r2'">
								<xsl:text>Unconditional entropy H(R) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c_r2'">
								<xsl:text>Conditional entropy H(C|R) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='mi2'">
								<xsl:text>Mutual information MI(C,R) normalized 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='aic2'">
								<xsl:text>Asymetric information coefficient AIC(R,C) 2</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='kend2'">
								<xsl:text>Kendall coefficient 2</xsl:text>
							</xsl:when>
							
							
							
							<xsl:when test="name()='da_sum'">
								<xsl:text>DA-Sum : Sum of absolute differences of all frequencies</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='da_min'">
								<xsl:text>DA-Min : Minimal absolute difference of corresponding frequencies</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='da_max'">
								<xsl:text>DA-Max : Maximal absolute difference of correspondint frequencies</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='dr_sum'">
								<xsl:text>D%-Sum : Sum of differences of relative frequencies</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='dr_min'">
								<xsl:text>D%-Min : Minimal difference of relative frequencies</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='dr_max'">
								<xsl:text>D%-Max : Maximal difference of relative frequencies</xsl:text>
							</xsl:when>
							

							
							
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->

					
		
					<attribute name="{name()}" value="{.}" label="{$label}" />
	</xsl:template>
	
	


















	<!-- zpracovani cedentu-->
	
	<xsl:template match="@row_attributes | @column_attributes | @condition | @set1 | @set2">

    <xsl:apply-templates select="id(.)" mode="values">
      <xsl:with-param name="cedent_type">
        <xsl:value-of select="name()"/>
      </xsl:with-param>
    </xsl:apply-templates>		

	</xsl:template>
	
	
	

	<!-- boolske literaly -> cedent -->
	<xsl:template match="ti_cedent" mode="values">
    <xsl:param name="cedent_type"/>

    <xsl:variable name="label">
      <xsl:choose>
        <xsl:when test="$cedent_type='condition'">Condition</xsl:when>
        <xsl:when test="$cedent_type='set1'">First set</xsl:when>
        <xsl:when test="$cedent_type='set2'">Second set</xsl:when>
        <xsl:otherwise>BooleanCedent</xsl:otherwise>
        <!--otherwise by nemelo nastat-->
      </xsl:choose>
    </xsl:variable>  
    
    	<xsl:variable name="hodnota_cedentu">
    		<xsl:apply-templates select="ti_literal" mode="values"/>
    	</xsl:variable>
    	<xsl:text disable-output-escaping="yes">
					</xsl:text>		
    	<attribute name="{$cedent_type}" value="{$hodnota_cedentu}" label="{$label}"/>	
	</xsl:template>
	
	
	
	<!-- kategorialni cedent -->
	<xsl:template match="ti_attribute" mode="values">
    <xsl:param name="cedent_type"/>

    <xsl:variable name="label">
      <xsl:choose>
        <xsl:when test="$cedent_type='row_attributes'">Row attributes</xsl:when>
        <xsl:when test="$cedent_type='column_attributes'">Column attributes</xsl:when>
        <xsl:otherwise>CategorialCedent</xsl:otherwise>
        <!--otherwise by nemelo nastat-->
      </xsl:choose>
    </xsl:variable>
    
		<xsl:text disable-output-escaping="yes">
					</xsl:text>		
    	<attribute name="{$cedent_type}" value="{@quant}" label="{$label}"/>
	</xsl:template>
	

	<!-- preformatuje boolsky literal -->
	<xsl:template match="ti_literal" mode="values">		
		
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no"> &amp; </xsl:text>
		</xsl:if>

		
		<xsl:value-of select="@quant"/>
		<xsl:text disable-output-escaping="yes">(</xsl:text>
		<xsl:value-of select="@value"/>
		<xsl:text disable-output-escaping="yes">)</xsl:text>
	</xsl:template>
	






</xsl:stylesheet>
